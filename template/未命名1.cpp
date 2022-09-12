bool mt(int p){
	if(p)return mt(0);
	else return mt(1);
}
mt(1);
