Jonathan Tousley
A01908436
CS 2420 - Dr. Vicki Allan
Assignment 5 - Priority Queues
j.tousley@live.com

Linux:
Type "make" without quotes to compile and run on g++. Remember to comment/uncomment lines 25-44 depending on which type of queue you want to use.


Comments on the overall complexity:
	D - ary heap:
		Insertion comparisons:
			Avg .5 comparisons/insertion = .5 << log2 160 = 7.3
		Merge comparisons:
			Avg 45 comparisons/merge = 45 >> log2 100 = 6.6
		Deletion comparisons:
			Avg 3 comparisons/deletion = 3 << log2 160

	Leftist Heap:
		Insertion comparisons:
			Avg 5 comparisons/insertion = log2 70
		Merge comparisons:
			Avg 10 comparisons/merge > log2 100
		Deletion comparisons:
			Avg 5 comparisons/deletion = log2 80

	Skew Heap:
		Inserstion Comparisons:
			Avg 5 comparisons/insertion = log2 80
		Merge comparisons:
			Avg 8 comparisons/merge = log2 100
		Deletion comparisons:
			Avg 5 comparisons/deletion = log2 80

