bool isMirrorR(TreeNode* t1,TreeNode* t2)
{
if(t1==NULL && t2==NULL)return true;
if(t1==NULL || t2==NULL)return false;

return isMirrorR(t1->left,t2->right) && isMirrorR (t1->right,t2->left);
}

bool isMirror(TreeNode* t)
{
	if(t==NULL)return true;
	return isMirrorR(t->left,t->right);
}

int sortedIndex[i];

makeTree(int sortedIndex[],i);

TreeNode* makeTree(int a[],int low, int high)
{
	if(high<low)return NULL;
	if(low==high){
		return newNode(a[low]);
	}
	else{
		int mid=(low+high)/2;
		TreeNode* result=newNode(a[mid]);
		result->left=makeTree(a,low,mid-1);
		result->right=makeTree(a,mid+1,high);
		return result;
	}
}