#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/in.h>
#include <linux/slab.h>
#include <linux/list.h>

struct packet_info {
    unsigned int src_ip;
    unsigned int dest_ip;
    unsigned short src_port;
    unsigned short dest_port;
    struct list_head list;
};

static struct nf_hook_ops nfho;
static LIST_HEAD(packet_list);

static unsigned int packet_sniffer_hook(void *priv,
                                        struct sk_buff *skb,
                                        const struct nf_hook_state *state) {
    struct iphdr *ip_header;
    struct tcphdr *tcp_header;
    struct udphdr *udp_header;
    struct packet_info *pkt;
    
    if (!skb)
        return NF_ACCEPT;

    ip_header = ip_hdr(skb);
    if (!ip_header)
        return NF_ACCEPT;

    pkt = kmalloc(sizeof(struct packet_info), GFP_KERNEL);
    if (!pkt)
        return NF_ACCEPT;

    pkt->src_ip = ip_header->saddr;
    pkt->dest_ip = ip_header->daddr;
    
    if (ip_header->protocol == IPPROTO_TCP) {
        tcp_header = tcp_hdr(skb);
        pkt->src_port = ntohs(tcp_header->source);
        pkt->dest_port = ntohs(tcp_header->dest);
        printk(KERN_INFO "[TCP] Src: %pI4:%u -> Dest: %pI4:%u\n", 
                &pkt->src_ip, pkt->src_port, &pkt->dest_ip, pkt->dest_port);
    } else if (ip_header->protocol == IPPROTO_UDP) {
        udp_header = udp_hdr(skb);
        pkt->src_port = ntohs(udp_header->source);
        pkt->dest_port = ntohs(udp_header->dest);
        printk(KERN_INFO "[UDP] Src: %pI4:%u -> Dest: %pI4:%u\n", 
                &pkt->src_ip, pkt->src_port, &pkt->dest_ip, pkt->dest_port);
    }

    list_add_tail(&pkt->list, &packet_list);
    return NF_ACCEPT;
}

static int __init packet_sniffer_init(void) {
    printk(KERN_INFO "Initializing Packet Sniffer Module...\n");
    nfho.hook = packet_sniffer_hook;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho);
    return 0;
}

static void __exit packet_sniffer_exit(void) {
    struct packet_info *pkt, *tmp;
    printk(KERN_INFO "Exiting Packet Sniffer Module...\n");
    nf_unregister_net_hook(&init_net, &nfho);
    list_for_each_entry_safe(pkt, tmp, &packet_list, list) {
        list_del(&pkt->list);
        kfree(pkt);
    }
}

module_init(packet_sniffer_init);
module_exit(packet_sniffer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Himanshu");
MODULE_DESCRIPTION("Kernel-Space Network Packet Sniffer using Structs & Linked List");
