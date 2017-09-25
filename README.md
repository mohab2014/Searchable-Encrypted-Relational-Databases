# Searchable-Encrypted-Relational-Databases
Inference Attacks on Searchable Encrypted Relational Databases

To the best of our knowledge, this is the first work that investigates the
security of relational databases protected by SSE schemes.

We propose three attacks on searchable encrypted relational databases
1. Relational-Count Attack: 
This attack requires only the attacker's knowledge about the frequency distribution of the protected   relational database under attack which is a reasonable requirement compared to the joint frequency knowledge required by previous inference attacks.

2. Attribute-Name Recovery Attack: 
This attack enables a passive adversary with only basic knowledge about the meta-data of the protected relational database to distinguish between observed queries whose attribute names are different. Assuming enough queries are issued, an attacker finds the queries belonging to the same attribute name or column.

3. Combining the above two attacks:
Under the assumption that all queries have been issued, we are able to show that the security provided by SSE schemes is equivalent to the security provided by determinitic encryption when it comes to protect a relational database.











#Compile & Run:


1. Implementation of the standard Count Attack proposed by Cash et al.
    compile: g++ -o countAttack countAttack.cpp -O3 -std=c++11
    
    run on the bank dataset[1]: ./countAttack bank3720/BANKSPECIALqueryClientlog.txt bank3720/observed1-3720-3720-special.txt 3720 bankKeywords.txt bankTest/observed1-3720-3720-test.txt 3720 4521 bankTest/bankTestClientlog.txt bankTest 
   
   or
   
   ./countAttack bankTest/bankTestClientlog.txt bankTest/observed1-3720-3720-test.txt 3720 bankKeywords.txt bank3720/observed1-3720-3720-special.txt 3720 4521 bank3720/BANKSPECIALqueryClientlog.txt bank3720/ 
   
  run on the Census dataset[2]:   ./countAttackPosted census3993/CENSUSTEST1queryClientlog.txt census3993/observed1-3993-3993-test1.txt 3993 census-keywords.txt census3993-2/observed1-3993-3993-test2.txt 3993 299285 census3993-2/CENSUSTEST2queryClientlog.txt census3993-2

   
   Note that the first execution assumes that the target data is bankTest where the attacker's goal is to break query privacy
   given the full frequency and joint frequency knowledge given from the bank3720 data. The second execution changes the roles
   in the first execution, so here bank3720 will be the target data and bankTest will be the known data.
   
2. Implementation of our Relational-Count Attack (Abdelraheem et al.):
   compile: g++ -o relationalCountAttack relationalCountAttack.cpp -O3 -std=c++11
   
   run on the bank dataset:  ./relationalCountAttack bank3720/BANKSPECIALqueryClientlog.txt bank3720/observed1-3720-3720-special.txt 3720 bankKeywords.txt bankTest/observed1-3720-3720-test.txt 3720 4521 bankTest/bankTestClientlog.txt bankTest 
  
  or
  
  ./relationalCountAttack bankTest/bankTestClientlog.txt bankTest/observed1-3720-3720-test.txt 3720 bankKeywords.txt bank3720/observed1-3720-3720-special.txt 3720 4521 bank3720/BANKSPECIALqueryClientlog.txt bank3720/ 

run on the Census dataset:
./relationalCountAttack census3993/CENSUSTEST1queryClientlog.txt census3993/observed1-3993-3993-test1.txt 3993 census-keywords.txt census3993-2/observed1-3993-3993-test2.txt 3993 299285 census3993-2/CENSUSTEST2queryClientlog.txt census3993-2
   
   
References:
1. https://archive.ics.uci.edu/ml/datasets/Bank+Marketing
2. https://archive.ics.uci.edu/ml/datasets/Census-Income+(KDD)
