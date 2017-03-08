#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <uapi/linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/types.h>

#define DRIVER_AUTHOR "JWGUO"
#define DRIVER_DESC "HELLO WORLD"

struct sk_buff *sock_buff;
static struct nf_hook_ops nfho;

/* Older kernel has different funcion definition. */
static unsigned int hook_func(
        const struct nf_hook_ops *ops,
        struct sk_buff *skb,
        const struct net_device *in,
        const struct net_device *out,
        int (*okfn)(struct sk_buff *))
{
    char *ifname = (char *)(in->name);
    struct ethhdr *mac_header = (struct ethhdr *)skb_mac_header(skb);
    struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);
    sock_buff = skb;

    if (!sock_buff) {
        return NF_ACCEPT;
    }

    // Do something to the pkt.
    printk(KERN_INFO "======net_dev: %s=====\n", ifname);

    printk(KERN_INFO "src_mac: %pM", mac_header->h_source);
    printk(KERN_INFO "dst_mac: %pM", mac_header->h_dest);

    printk(KERN_INFO "src_ip: %pI4", &ip_header->saddr);
    printk(KERN_INFO "dst_ip: %pI4", &ip_header->daddr);

    printk(KERN_INFO "\n");
    return NF_ACCEPT;
}

static int __init init_main(void)
{
    nfho.hook = hook_func;
    nfho.hooknum = NF_INET_PRE_ROUTING; // For older kernel: NF_IP_PRE_ROUTING
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;
    nf_register_hook(&nfho);

    printk(KERN_INFO "Successfully inserted a hook into kernel\n");

    return 0;
}

static void __exit cleanup_main(void)
{
    nf_unregister_hook(&nfho);

    printk(KERN_INFO "Successfully unloaded the hook\n");
}

module_init(init_main);
module_exit(cleanup_main);

MODULE_LICENSE("GPLv3");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

