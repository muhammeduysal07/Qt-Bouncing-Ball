#include "top.h" // Top sınıfının tanımının (header) olduğu dosyayı dahil et.

// Yapıcı Fonksiyon (Constructor): Top nesnesi oluşturulduğunda çalışır.
// Top, QLabel(parent) mirasçısı olduğu için, QLabel'in yapıcı fonksiyonunu çağırır ve ebeveyni (parent) atar.
Top::Top(QWidget *parent) : QLabel(parent)
{
    // setPixmap: Topun görselini ayarlar.
    // QPixmap(":/resimler/resimler/0.jpg"): Kaynak dosyasından (resimler.qrc) top resmini yükler.
    setPixmap(QPixmap(":/resimler/resimler/0.jpg"));

    // setScaledContents: İçeriğin (resmin) etiketin boyutuna göre ölçeklenmesini sağlar.
    // Yani, Top'un boyutu değişirse resim de sığacak şekilde küçülüp büyür.
    setScaledContents(true);

    // setGeometry: Topun ilk konumunu (0, 0) ve boyutunu (50x50) ayarlar.
    setGeometry(0, 0, 50, 50);

    // setVisible: Topun başlangıçta görünür olmasını sağlar (true).
    setVisible(true);
}
