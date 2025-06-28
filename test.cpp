class Bank{
public:
    int money;
};
int main(){
    int Bank::* m=&Bank::money;
    return 0;
}