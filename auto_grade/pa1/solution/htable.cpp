#include <iostream>
#include <string>


struct pair
{
    bool filled;
    int key;
    std::string value;
};


class hash_table
{
    int hash(int key);

    public:
    pair* table;

    int TABLE_SIZE=5;
    int load=0;
    bool resize();
    bool deletes(int key);
    bool print();
    bool insert(int key, std::string value);
    int lookup(int key);  //returns position
    hash_table();
    ~hash_table();
};

hash_table::hash_table() 
{
    table=new pair[TABLE_SIZE];
    for(int i=0;i<TABLE_SIZE;i++) {
        table[i].filled=0;
    }
}

hash_table::~hash_table() 
{
    delete [] table;
    table = NULL;
}

int hash_table::hash(int key)
{
    return (key % 443) % TABLE_SIZE;
}

bool hash_table::resize()
{
    pair* temp=table;
    TABLE_SIZE=TABLE_SIZE*2;
    table=new pair[TABLE_SIZE];
    load=0;

    for(int i=0;i<TABLE_SIZE;i++)
        table[i].filled=0;

    for(int i=0;i<TABLE_SIZE/2;i++) {
        if (temp[i].filled)
            insert(temp[i].key,temp[i].value);
    }
    delete [] temp;
    temp = NULL;
    std::cout << "table doubled" << std::endl;
    return 1;

}

int hash_table::lookup(int key)
{
    int thehash = hash(key);
    for(int i=0;i<TABLE_SIZE;i++) {
        if ((table[(thehash+i)%TABLE_SIZE].filled)
                && (table[(thehash+i)%TABLE_SIZE].key == key)) {
            return (thehash+i)%TABLE_SIZE;
        }
    }
    return -1;
}

bool hash_table::deletes(int key)
{
    int location = lookup(key);
    if (location >= 0) {
        table[location].filled = 0;
        load--;
        return 1;
    }
    else 
        return 0;
}

bool hash_table::print()
{
    for(int i=0;i<TABLE_SIZE;i++) {
        if (table[i].filled)
            std::cout << "(" << table[i].key << "," << table[i].value << ")";
    }
    std::cout << std::endl;
    return 1;
}

bool hash_table::insert(int key, std::string value)
{
    int thehash = hash(key);
    for(int i=0;i<TABLE_SIZE;i++) {
        if (!table[(thehash+i)%TABLE_SIZE].filled) {
            table[(thehash+i)%TABLE_SIZE].filled = 1;
            table[(thehash+i)%TABLE_SIZE].key = key;
            table[(thehash+i)%TABLE_SIZE].value = value;
            load++;
            return 1;
        }
        else if (table[(thehash+i)%TABLE_SIZE].key == key) {
            return 0;
        }
    }
    return 0;
}



int main()
{
    hash_table table;
    int key;
    std::string value;
    std::string input="";

    int success;
    int location;
    
    while(true) {
        std::cin >> input;
        if(std::cin.eof())
            return 0;

        if (input=="insert") {
            std::cin >> key;
            std::cin >> value;
            success = table.insert(key,value);

            if (success) 
                std::cout << "item successfully inserted" << std::endl;
            else
                std::cout << "item already present" << std::endl;

            if (10*table.load > 7*table.TABLE_SIZE) {
                table.resize();
            }
        }
        else if (input=="lookup") {
            std::cin >> key;
            location = table.lookup(key);
            if (location >=0) {
                std::cout << "item found; " << table.table[location].value;
                std::cout << " " << location << std::endl;
            }
            else
                std::cout << "item not found" << std::endl;
        }
        else if (input=="delete") {
            std::cin >> key;
            success = table.deletes(key);
            if (success)
                std::cout << "item successfully deleted" << std::endl;
            else 
                std::cout << "item not present in the table" << std::endl;
        }
        else if (input=="print") {
            table.print();
        }
        else {
            std::cout << "Unexpected Input." << std::endl;
            return 1;
        }

    }
    return 0;
}
