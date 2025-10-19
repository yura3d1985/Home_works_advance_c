void btUpView(tree *root)
{    	
	if(root == NULL)	return;
	
	tree *tmp = root;
	
	int p = 0;
	
	while(tmp) 
	{
		tmp = tmp->left;
		p++;
	}

	tmp = root;
	
	while(p > 1)
	{
		for(int i = 1; i < p; i++) tmp = tmp->left;  
		printf("%d ",tmp->key);
		tmp = root;
		p = p - 1;
	}

	while(root)
	{
		printf("%d ",root->key);
		root = root->right;
	} 
}
