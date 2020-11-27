bool insert(Etype &x, TreeNode<Etype> *&t){
	if(t==NULL){
		t=new TreeNode<Etype>(x);
		return true;
	}
	if(x<t->element)
		return insert(x,t->left);
	else
		return insert(x,t->right);
}

/*
AVL Trees

*/