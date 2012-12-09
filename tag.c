#include "tag.h"

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


