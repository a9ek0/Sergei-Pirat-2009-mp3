#include "lyb/menu.h"
#include "lyb/cache.h"


/////dobavit proverku na enter
////mb ubrat canon iz vibora chto dobavit

int main() {

    CACHE *cache;
    char file_name[16] = "domain_list.txt";

    cache = create_cache();

    menu(cache, file_name);

    free_cache(cache);
    return 0;
}
