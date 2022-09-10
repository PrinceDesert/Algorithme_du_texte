## Pré-requis :
- Installer Make
- Système d'exploitation Linux 

## Configuration
```make mrproper``` : supprimer tous les fichiers générés
```make clean``` : supprimer tous les fichiers objets et éxécutables dans les dossiers obj et bin

```make start_build``` : créer les dossiers obj, lib et bin

```make transition_matrix_trie``` : compiler et éxécuter avec la représentation par la matrice de transition

```make hash_table_trie``` : compiler et éxécuter avec la représentation par un table de hachage
(possibilité d'éxécuter cette commande pour créer plusieurs client)
