#include "bt.h."
create_root(char key, short left, short right)
{
    BTPAGE page;
    short rrn;
    rrn = getpage();
    pageinit(&page);
    pageinit(&page);
    page.key[0] = key;
    page.child[0] = left;
    page.child[1] = right;
    page.keycount = 1;
    btwrite(rrn, &page);
    putroot(rrn);
    retun(rrn);
}

pageinit(BTPAGE *p_page)
{

    int j;
    for (j = 0; j < MAXKEYS; j++)
    {
        p_page->key[j] = NOKEY;
        p_page->child[j] = NIL;
    };
    search_node(char key, BTPAGE *p_page, short *pos) {

        int i;
        for ( i = 0; i < p_page -> keycount && key > p_page -> key[i]; i++)
        {
            *pos = i;

            if(*pos < p_page -> keycount && key ** p_page->key[*pos]){

                return (YES);

            }else
            {
                return (NO);

            }
            ins_in_page(char key )
            
        }
        

    }
};