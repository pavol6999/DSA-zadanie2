
#include <stdlib.h>
#include <stdio.h>



int primeNumbers[] = {3126547, 5190071,8615527, 14301779,28603583,57207221};
int PrimeIndex = 1;

typedef struct entry {
    int key;
    struct entry* next;
} ENTRY;

typedef struct {
    int entries;
    int size;
    ENTRY** bucket;
}h_table;

//kedze insert() zahrnuje funkciu resize() a resize() zahrnuje funckiu insert(), musime definovat jednu z nich na zaciatku
void insert(h_table* table, int key);


int hash(int key, int table_size) {
    return key % table_size;
}


// alokacia novej tabylky, vsetky vedierka su automaticky nastavene na NULL aby sme dalej s nimi vedeli lahsie pracovat
// v kazdej funkcii testujem malloc
h_table* create_hashTable(int table_size) {


    h_table* table;
    if ((table = malloc(sizeof(h_table))) == NULL)
        return NULL;

    table->bucket = malloc(sizeof(ENTRY*) * table_size);


    for (int i = 0; i < table_size; i++) {
        table->bucket[i] = NULL;
    }
    table->entries = 0;
    table->size = table_size;

    return table;

}
//funkcia resize mi zvacsi hashovaciu tabulku ak je pomer zaplnenia (pocet parov/velkost tabulky) vacsi ako 75%
void resize_table(h_table* old_table) {

    //jedina globalna premenna, je list prvocisel, index ukazuje na prve z nich a bude sa inkrementovat po kazdom zvacseni

    h_table* newTable;

    int newPrime= primeNumbers[PrimeIndex];
    //vytvorim novu tabulku
    newTable = create_hashTable(newPrime);

    //zvacsi sa mi index, ktory ukazuje na novu velkost hash tabulky pri pripadnom resize()
    //aby som nepouzival staticku premennu, vedel by som to obist tak, ze zdvojnasobim
    //velkost tabulky a nasilu budem cislo iterovat dokym nebude prvocislo
    PrimeIndex++;

    //kedze hash funkcia pracuje s modulo velkost tabulky, musim vsetky prvky zo starej hash tabulky znovu vlozit do vacsej tabulky,
    //inak by sa prvky stale ukladali na index (0, velkost old_table)
    for (int i = 0; i < old_table->size; i++) {
        ENTRY* entry = old_table->bucket[i];
        while (entry != NULL) {
            //vdaka znovu vlozeni prvkov z old_table do newTable, sa moze stat a je ocakavane ze dva prvky ktore boli v old_table na tom istom indexe
            //za sebou budu oddelene a naopak.
            insert(newTable, entry->key);
            entry = entry->next;
        }
    }
    old_table->size = newTable->size;
    old_table->bucket = newTable->bucket;






}

//vytvorenie noveho paru key, data
ENTRY* put(int key) {
    ENTRY* entry;
    if ((entry = malloc(sizeof(ENTRY*))) == NULL)
        return NULL;


    entry->next = NULL;
    entry->key = key;


    return entry;
}


int checkRatio(h_table* table) {
    double ratio = (double)table->entries / (double)table->size;
    if (ratio >= 0.75){
        return 1;}
    return 0;
}


void insert(h_table* table, int key) {
    //ak nebola inicializovana hash table
    if (table == NULL)
        return;

    //pokusim sa najst, kde by sa prvok mohol vyskytovat keby bol v hash tabulke pomocou hash funkcie
    //z toho mi vyplyvaju dve vychodiskove cesty
    ENTRY* entry = table->bucket[hash(key, table->size)];

    // 1. ak je vedierko prazdne, vlozime novy  key + vypocitame pomer naplnenia
    if (entry == NULL) {
        table->bucket[hash(key, table->size)] = put(key);
        (table->entries)++;
        if (checkRatio(table)){
        resize_table(table);}
        return;
    }


    ENTRY* previous = entry;
    //2. ak je vedierko plne uz, prechadzam listom
    while (entry != NULL)
    {
        // 2.a) ak sme nasli kluc totozny s vlozenym klucom
        if (entry->key == key) {
            return;
        }
        previous = entry;
        entry = entry->next;
    }
    // 2.b) ak sme prisli na koniec listu, tak na posledne miesto pridam novy key+ spocitam pomer naplnenia
    previous->next = put(key);
    (table->entries)++;
    if (checkRatio(table)) {
        resize_table(table);
    }
}



ENTRY* search(h_table* table, int key) {
    //ak je kluc prazdny, alebo tabulka nebola inicializovana
    if (table == NULL)
        return NULL;
    //najskor najdeme, kde by sa v tabulke mohla dvojica nachadzat podla hash(key)
    ENTRY* searched = table->bucket[hash(key, table->size)];

    //ak v danom vedierku  je nejaky par, prebehnem cez cely zoznam v danom vedierku, dokym nedostanem data patriace klucu
    while (searched != NULL) {
        if (searched->key == key) {
            return searched;
        }
        searched = searched->next;
    }
    //ak sa mi to nepodarilo, tak to znamena, ze sa dany kluc nenachadza v hashovacej tabulke, vrati null
    return NULL;

}


