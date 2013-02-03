

#ifndef __PAGE_EDITOR_CODEC_H_
 #define __PAGE_EDITOR_CODEC_H_


#include <QWidget>


class AppSettings;
class QListWidgetItem;

namespace Ui {
class PageEditorCodec;
}


namespace Wolverine {
namespace Settings {


class PageEditorCodec : public QWidget
{
    Q_OBJECT
    
public:
    explicit PageEditorCodec(AppSettings *settings, QWidget *parent = 0);
    ~PageEditorCodec();
    
private slots:
    void onSelectAll();
    void onUnselectAll();
    void onItemClicked(QListWidgetItem *item);

private:
    AppSettings *mSettings;

    Ui::PageEditorCodec *ui;
};

}
}

#endif // __PAGE_EDITOR_CODEC_H_
