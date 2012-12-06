typedef unsigned int __u32;
typedef unsigned char __u8;
typedef unsigned short __u16;

struct tag_header {
	__u32 size;
	__u32 tag;
};
struct tag_core {
	__u32 flags;	/* bit 0 = read-only */
	__u32 pagesize;
	__u32 rootdev;
};
struct tag_mem32 {
	__u32	size;
	__u32	start;	/* physical start address */
};

struct tag_initrd {
	__u32 start;	/* physical start address */
	__u32 size;	    /* size of compressed ramdisk image in bytes */
};

struct tag_cmdline {
	char	cmdline[1];	/* this is the minimum size */
};

struct tag {
	struct tag_header hdr;
	union {
		struct tag_core		core;
		struct tag_mem32	mem;
		struct tag_initrd	initrd;
		struct tag_cmdline	cmdline;
	} u;
};

#define tag_next(t)	((struct tag *)((__u32 *)(t) + (t)->hdr.size))
#define tag_size(type)	((sizeof(struct tag_header) + sizeof(struct type)) >> 2)


/* The list must start with an ATAG_CORE node */
#define ATAG_CORE	0x54410001
/* it is allowed to have multiple ATAG_MEM nodes */
#define ATAG_MEM	0x54410002
/* describes where the compressed ramdisk image lives (physical address) */
#define ATAG_INITRD2	0x54420005
/* The list ends with an ATAG_NONE node. */
#define ATAG_NONE	0x00000000
/* command line: \0 terminated string */
#define ATAG_CMDLINE	0x54410009

const char cmd[] = "root=/dev/nfs rw nfsroot=192.168.81.72:/opt/nfsroot/myrootfs_tiny210 ip=192.168.81.123:192.168.81.72:192.168.81.1:255.255.255.0:tiny210:eth0:off console=ttySAC0 console=tty1,115200 init=/linuxrc";


void init_taglist(void)
{
	struct tag * p;
	int i;
	/* setup start tag */
	p = (struct tag*) 0x22000000;
	p->hdr.tag  =  ATAG_CORE;
	p->hdr.size = tag_size(tag_core);
	p->u.core.flags = 0;
	p->u.core.pagesize = 0;
	p->u.core.rootdev = 0;

	p = tag_next(p);
	/* setup memory tags */
	p->hdr.tag = ATAG_MEM;
	p->hdr.size = tag_size(tag_mem32);
	p->u.mem.size = 512*1024*1024;
	p->u.mem.start = 0x20000000;

	p = tag_next(p);
	/* setup commandline tag */
	p->hdr.tag = ATAG_CMDLINE;
	p->hdr.size =  (sizeof (cmd) + sizeof(struct tag_header) + 3) >>2;	
	for(i=0; i< sizeof (cmd); i++)	
		p->u.cmdline.cmdline[i] = cmd[i];

	p = tag_next(p);
	/* setup end tag */
	p->hdr.tag = ATAG_NONE;
	p->hdr.size = 0;
}


