#ifndef FILECONTAINER_H
#define FILECONTAINER_H
#include "filecontainer/file.h"

#include <QObject>
#include <QHash>

namespace  rotable {
    class FileContainer;
}

class rotable::FileContainer : public QObject
{
    Q_OBJECT
public:
    explicit FileContainer(QObject *parent = 0);

    ~FileContainer();

    void addFile(File *file);

    QList<int> fileIds() const;

    int count() const;

    File* file(int idx) const;

    /**
     * @brief Clear object
     *
     */
    void clear();
    File* getSelectedFile() const;
    void setSelectedFile(File *value);
    void setSelectedFile(int inx);

signals:
    /**
     * @brief
     *
     * @param user
     */
    void fileAdded(File *file);
    /**
     * @brief
     *
     */
    void fileRemoved();
    /**
     * @brief
     *
     */
    void fileUpdated();
    /**
     * @brief
     *
     */
    void updateView();
private:
    QHash <int,  File*> _files; /** Container with files */
    File *selectedFile;
};

#endif // FILECONTAINER_H
