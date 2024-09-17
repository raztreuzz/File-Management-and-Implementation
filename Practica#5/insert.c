#include "bt.h."

/*insertt()..
Arguments:
rrn:
*promo_r_child:
*promo_key:

*/

insertt(short rrn, char key, short promo_r_child, char *promo_key)
{
    BTPAGE page,newpage;
    int found,promoted;
    short pos, p_b_rrn;
    char p_b_key;

    if (rrn == NIL)
    {
        *promo_key = key;
        *promo_r_child = NIL;
        return (YES);
    }
    
    
}