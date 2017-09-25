# Searchable-Encrypted-Relational-Databases
Inference Attacks on Searchable Encrypted Relational Databases

To the best of our knowledge, this is the first work that investigates the
security of relational databases protected by SSE schemes.

We propose three attacks on searchable encrypted relational databases
1. Relational-Count Attack: this attack requires only the attacker's knowledge about the frequency distribution of the protected   relational database under attack which is a reasonable requirement compared to the joint frequency knowledge required by previous inference attacks.

2. Attribute-Name Recovery Attack: this attack enables a passive adversary with only basic knowledge about the meta-data of the protected relational database to distinguish between observed queries whose attribute names are different. Assuming enough queries are issued, an attacker finds the queries belonging to the same attribute name or column.

3. Combining the above two attacks and under the assumption that all queries have been issued, we are able to show that the security provided by SSE schemes is equivalent to the security provided by determinitic encryption when it comes to protect a relational database.
