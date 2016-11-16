#ifndef FILECONTAINER_H
#define FILECONTAINER_H
#include "filecontainer/file.h"

#include <QObject>

class FileContainer : public QObject
{
    Q_OBJECT
public:
    explicit FileContainer(QObject *parent = 0);

    ~FileContainer();

    void addFile(rotable::File *file);

    QList<int> fileIds() const;

    int count() const;

    rotable::File* file(int idx) const;

    /**
     * @brief Clear object
     *
     */
    void clear();
    rotable::File* *getSelectedFile() const;
    void setSelectedFile(User *value);
    void setSelectedFile(int inx);

signals:
    /**
     * @brief
     *
     * @param user
     */
    void fileAdded(rotable::File *file);
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
    QHash <int, rotable::File*> _files; /** Container with files */
    rotable::File *selectedFile;
};

#endif // FILECONTAINER_H
