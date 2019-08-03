#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
template<class T>
class Btree{
	protected:
	    //Guardar o grau mínimo da árvore
		static const int t = 3;
		struct Node{
			bool leaf;
			//Guardar a quantidade de chaves que há no nó
			int nKeys;
			//criou número máximo de ponteiros para os filhos
			Node *child[2*t+1];
			//número mínimo de filhos
			T tkey[t+1];
			//Zerando os atributos
			Node(bool leaf = true, int nKeys =0) : leaf (leaf), nKeys(nKeys){}
		};
		// Nó raiz da árvore
		Node *Root;
		int nNodes;
		//Destrutor
		~Btree();
    public:
        //Construtor
        Btree(){
            nNodes = 0;
            BtreeCreate();
        }

       //O procedimento abaixo pesquisa na árvore uma determinada chave, passando um ponteiro para o nó e a chave a ser pesquisada.
        Node *BtreeSearch(Node *x,T key){
            int i = 1;
            while (i<=x.nKeys&&key>x.tkey[i]){
                i++;
            }
            if(i<=x.nKeys && key==x.tkey[i]){
               return (x,i);
            }else if(x.leaf==true){
                return NULL;
            }else{
                DiskRead(x.child[i]);
                return BtreeSearch(x.child[i],key);
            }
        }

    private:
        //O procedimento abaixo aloca um novo nó na árvore
        Node *AlocateNode(){
            Node *node = new Node();
            nNodes++;
            #ifdef DEBUG
                cout << "Um novo nó foi alocado!" << endl;
            #endif
            return node;
        }
        //A função abaixo faz a operação de escrita em memória
        void DiskWrite(Node *x){
            #ifdef DEBUG
                cout << "Disk Write" << endl;
            #endif
        }
        //A função abaixo faz a operação de leitura em memória
        void DiskRead(Node *x){
            #ifdef DEBUG
                cout << "Disk Read" << endl;
            #endif
        }
        //A função abaixo cria uma árvore vazia
        void BtreeCreate(Btree){
            Node *x = new Node();
            x = AlocateNode();
            x.leaf = true;
            x.nKeys = 0;
            DiskWrite(Root);
            Root = x;
        }
        //A função abaixo faz o split child, em um nó que está cheio na hora da inserção
        void BtreeSplitChild(Node *x,int i){
            Node *z = AlocateNode();
            Node *y = x.child[i];
            z.leaf = y.leaf;
            z.nKeys = t - 1;
            int j;
            for(j=1;j==t-1;j++){
                z.tkey[j] = y.tkey[j+t];
            }
            if(y.leaf == false){
                for(j=1;j==t;j++){
                    z.child[j] = y.child[j+1];
                }
            }
            y.nKeys = t-1;
            for(j = x.nKeys;j=i+1;j++){
                    x.child[j+1] = x.child[j];
            }
            x.child[i+1] = z;
            for(j=x.nKeys;j=i;j++){
                x.tkey[j+1]=x.tkey[j];
            }
            x.tkey[i]=y.tkey[t];
            x.nKeys = x.nKeys++;
            DiskWrite(y);
            DiskWrite(z);
            DiskWrite(x);
        }
        //A função abaixo insere uma chave em um nó não completo
        void BtreeInsertNonFull(Node *x,T key){
            int i = x.nKeys;
            if(x.leaf==true){
                while(i>=1 && key<x.tkey[i]){
                    x.tkey[i+1] = x.tkey[i];
                    i--;
                }
                x.tkey[i+1] = key;
                x.nKeys++;
                DiskWrite(x);
            }
            else{
                while(i>=1 && key<x.tkey[i]){
                    i--;
                }
                i++;
                DiskRead(x.child[i]);
                if (x.child[i].nKeys == (2*t+1)){
                    BtreeSplitChild(x,i);
                    if (key > x.tkey[i]){
                        i++;
                    }
                    BtreeInsertNonFull(x.tkey[i],key);
                }
            }
        }
        //A função abaixo faz a inserção de uma chave na árvore
        void BtreeInsert(Btree tree,T key){
            Node *r = tree.Root;
            Node *s;
            if(r.nKeys==(2*t-1)){
               s = AlocateNode();
               tree.Root = s;
               s.nKeys = 0;
               s.child[1] = r;
               BtreeSplitChild(s,1);
               BtreeInsertNonFull(s,key);
            }else{
                BtreeInsertNonFull(r,key);
            }
        }
        //O procedimento abaixo encontra o filho predecessor de uma chave
        T PrecedingChild(Node *x){
            while(!x->leaf){
                x = x->child[x->nKeys+1];
            }
            return x->tkey[x->nKeys];
        }
        //O procedimento abaixo encontra o filho sucessor de uma chave
        T SuccessorChild(Node *x){
            while(!x->leaf){
                x=x->child[1];
            }
            return x->tkey[1];
        }
        //A função abaixo encontra a chave predecessora de uma determinada chave
        void FindPredecessor(T key,Node *x){}
        //A função abaixo encontra a chave sucessora de uma determinada chave
        void FindSuccessor(T key,Node *x){}
        //A função abaixo move três chaves de lugar
        void MoveKey(T Key, Node *x1,Node *x2){}
        //A função abaixo fundi dois nós
        void MergeNodes(Node *x1,Node *x2){}
        //A função abaixo remove uma chave
        void RemoveKey(T key, Node *x){}
        //A função abaixo encontra o filho que pode assumir o lugar de uma determinada chave
        void FindSibling(Node *w){}
        //A função abaixo trabalha em conjunto com outras funções para fazer a operação de retirada da árvore nos determinados casos
        void BtreeDeleteKey(T key, Node *x){
            Node *y,*z;
            T lkey;
            if (x.leaf == false){//Não é folha! Caso 2
                y = PrecedingChild(x);
                z = SuccessorChild(x);
                if (y.nKeys > (t-1)){
                    lkey = FindPredecessor(key, x);
                    MoveKey(lkey,y,x);
                    MoveKey(key,x,z);
                    BtreeDeleteKey(key,z);
                }else if(z.nKeys>(t-1)){
                    lkey = FindSuccessor(key, x);
                    MoveKey(lkey,z,x);
                    MoveKey(key,x,y);
                    BtreeDeleteKey(key,y);
                }else{
                    MoveKey(key,x,y);
                    MergeNodes(y,z);
                    BtreeDeleteKey(key,y);
                }
            }else if(x.leaf==true){//é Folha! Caso 1 ou 3
                y = PrecedingChild(x);
                z = SuccessorChild(x);
                Node *w = Node(Root);
                Node *v = Node(x);
                if (x.nKeys > t-1){
                    RemoveKey(key,x);
                }else if(y.nKeys > t-1){
                    lkey = FindPredecessor(w,v);
                    MoveKey(lkey,y,w);
                    lkey = FindSuccessor(w,v);
                    MoveKey(lkey,w,x);
                    BtreeDeleteKey(key,x);
                }else if(w.nKeys> (t-1)){
                    lkey = FindSuccessor(w,v);
                    MoveKey(lkey,w,x);
                    lkey = FindPredecessor(w,v);
                    MoveKey(lkey,w,x);
                    BtreeDeleteKey(key,x);
                }else{
                    Node *s;
                    s = FindSibling(w);
                    Node *lw = Node(Root);
                    if (lw.nKeys==(t-1)){
                        MergeNodes(lw,w);
                        MergeNodes(w,s);
                        BtreeDeleteKey(key,x);
                    }else{
                        MoveKey(v,w,x);
                        BtreeDeleteKey(key,x);
                    }
                }
            }
        }
};
#endif // HEADER_H_INCLUDED
