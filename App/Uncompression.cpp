#include "Uncompression.h"
#include <QMessageBox>

using namespace std ;

int copy_data( archive *ar,  archive *aw)
{
    int r;
    const void *buff;
    size_t size;
    long long int offset;

    for (;;)
    {
        r = archive_read_data_block(ar, &buff, &size, &offset);
        if (r == ARCHIVE_EOF) return ARCHIVE_OK ;

        if (r < ARCHIVE_OK)
        {
            QMessageBox::critical(0,
                                  "Erreur - Décompression du Comic Book",
                                  "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(ar))) ;
            return r ;
        }
        r = archive_write_data_block(aw, buff, size, offset);
        if (r < ARCHIVE_OK)
        {
            QMessageBox::critical(0,
                                  "Erreur - Décompression du Comic Book",
                                  "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(ar))) ;
            return r ;
        }
    }
}


string uncompressArchive (string path_to_archive, string destination_folder)
{
    struct archive *a;
    struct archive *ext;
    struct archive_entry *entry;
    int flags;
    int r;

    // Spécifier le dossier d'extraction de l'archive:
    // http://stackoverflow.com/questions/8384266/libarchive-extract-to-specified-directory

    flags |= ARCHIVE_EXTRACT_PERM;
    flags |= ARCHIVE_EXTRACT_ACL;
    flags |= ARCHIVE_EXTRACT_FFLAGS;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);
    ext = archive_write_disk_new();
    archive_write_disk_set_options(ext, flags);
    archive_write_disk_set_standard_lookup(ext);
    if ((r = archive_read_open_filename(a, path_to_archive.c_str(), 10240)))
    {
        QMessageBox::critical(0,
                              "Erreur - Décompression du Comic Book",
                              "La décompression ne s'est pas effectuée car le Comic Book spécifié est introuvable.") ;
        return "" ;
    }

    string path_to_uncompressed_folder = "" ;
    bool first_iteration = true ;
    for (;;)
    {
        //  Lecture des entêtes de l'archive les uns après les autres.
        r = archive_read_next_header(a, &entry);
        if (r == ARCHIVE_EOF)
            break ;
        if (r < ARCHIVE_OK)
        {
            QMessageBox::critical(0,
                                  "Erreur - Décompression du Comic Book",
                                  "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(a))) ;
            break ;
        }
        if (r < ARCHIVE_WARN)
        {
            QMessageBox::critical(0,
                                  "Erreur - Décompression du Comic Book",
                                  "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(a))) ;
            break ;
        }

        //  Écriture des fichier décompressés sur le disque.
        const char* currentFile = archive_entry_pathname(entry);
        if (first_iteration)
        {
            first_iteration = false ;
            path_to_uncompressed_folder = destination_folder + string(currentFile) ;
        }

        const string fullOutputPath = destination_folder + string(currentFile);
        archive_entry_set_pathname(entry, fullOutputPath.c_str());
        r = archive_read_extract(a,entry, flags) ;
        if (r < ARCHIVE_OK)
        {
            QMessageBox::critical(0,
                                  "Erreur - Décompression du Comic Book",
                                  "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(a))) ;
            break ;
        }
        else if (archive_entry_size(entry) > 0)
        {
            r = copy_data(a, ext);
            if (r < ARCHIVE_OK)
            {
                QMessageBox::critical(0,
                                      "Erreur - Décompression du Comic Book",
                                      "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(a))) ;
                break ;
            }
            if (r < ARCHIVE_WARN)
            {
                QMessageBox::critical(0,
                                      "Erreur - Décompression du Comic Book",
                                      "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(a))) ;
                break ;
            }
        }

        r = archive_write_finish_entry(ext);
        if (r < ARCHIVE_OK)
        {
            QMessageBox::critical(0,
                                  "Erreur - Décompression du Comic Book",
                                  "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(a))) ;
            break ;
        }
        if (r < ARCHIVE_WARN)
        {
            QMessageBox::critical(0,
                                  "Erreur - Décompression du Comic Book",
                                  "La décompression ne s'est pas effectuée correctement.\nMessage d'erreur: " + QString(archive_error_string(a))) ;
            break ;
        }
    }
    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    return path_to_uncompressed_folder ;
}
