#ifndef UNCOMPRESSION
#define UNCOMPRESSION

#include <archive.h>
#include <archive_entry.h>
#include <string>

//  Descr:  Écrit les données contenues dans ar sur le disque dur.
int copy_data( archive *ar,  archive *aw) ;


//  Descr:  Décompresse une archive.
//  Param:  * path_to_archive:      chemin vers l'archive à décompresser.
//          * destination_folder:   dossier où décompresser l'archive.
std::string uncompressArchive (std::string path_to_archive, std::string destination_folder) ;

#endif // UNCOMPRESSION

