#include <stdio.h>
#include "bt.h."
#include "fileio.h"

int btfd;

btopen()
{
    btfd = open("btree.dat", O_RDWR);
    return (btfd > 0);
}
btclose(){
    close(btfd);
};
short getroot();
{
    short root;
    long Iseek();

    lseek(btfd, 0L,0);
    if (read(btfd, &root,2) == 0)
    {
        printf("Error: no se pudo leer la raiz del arbol\n");
        exit(1);

    }
    return root;
}
putroot(short root);
{
    Iseek(btfd, 0L,0);
    write(btfd,&root,2);

}
short create_tree()
{
    char key;

    btfd = creat("btree.dat", PMODE);
    close(btfd);
    btopen();
    key = getchar();
    return (create_root(key,NIL,NIL));


}

short getpage(){
    long Iseek(),addr;
    addr = Iseek(btfd,0L,2) -2l;
    return ((short)addr /PAGESIZE);

}

btwrite(short rrn,BTPAGE,BTPAGE *page_ptr)
{   
    long Iseek(),addr;
    addr = (long)rrn *(long) PAGESIZE + 2L;
    Iseek(btfd,addr,0);
    return (write(btfd,page_ptr,PAGESIZE));
};
