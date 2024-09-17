#include <stdio.h>
#include "bt.h."

int main()
{

    int promoted;
    short root,
        promo_rrn;
    char promo_key, key;

    if (btopen())
    {
        root = getroot();
    }
    else
    {
        root = create_tree();
    }

    while ((key = getchar()) != 'q')
    {
        promoted = insert(root, &promo_rrn, &promo_key);
        if (promoted)
        {
            root = create_root(promo_key, root, promo_rrn);
        }
    }

    btclose();
}
