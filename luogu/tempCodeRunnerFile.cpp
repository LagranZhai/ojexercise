
    }
    build(1,1,n);
    for(int i{1};i<=m;i++){
        int stop{++maxp},nostop{++maxp};
        for(int j:train[i]){
            addedge(nodetocnt[j],stop);
        }
        int last{train[i][0]};
        for(int k{1};k<train[i].size();k++){
            int j{train[i][k]};
            if(j-1>=last+1){
                modify(1,1,n,last+1,j-1,nostop);
            }
            last=j;
        }
        addedge(stop,nostop);
    }
    maxp++;
    for(int i{1};i<=n;i++){
        addedge(maxp,nodetocnt[i]);