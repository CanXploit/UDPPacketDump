#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void handler(u_char* args, const struct pcap_pkthdr* header, const u_char* packet)
{
    struct ip* ip_hdr = (struct ip*)(packet + 14);
    if (ip_hdr->ip_p != IPPROTO_UDP) return;

    struct udphdr* udp_hdr = (struct udphdr*)((u_char*)ip_hdr + ip_hdr->ip_hl * 4);

    printf("%s:%d -> %s:%d\n",
        inet_ntoa(ip_hdr->ip_src),
        ntohs(udp_hdr->uh_sport),
        inet_ntoa(ip_hdr->ip_dst),
        ntohs(udp_hdr->uh_dport));
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("usage: %s <interface>\n", argv[0]);
        return 1;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(argv[1], BUFSIZ, 1, 1000, errbuf);
    if (!handle) {
        printf("pcap_open_live failed: %s\n", errbuf);
        return 1;
    }

    struct bpf_program fp;
    pcap_compile(handle, &fp, "udp", 0, PCAP_NETMASK_UNKNOWN);
    pcap_setfilter(handle, &fp);

    pcap_loop(handle, 0, handler, NULL);
    pcap_close(handle);
    return 0;
}
