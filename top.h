// "Header Guard" (Başlık Koruması): Bu dosyanın projeye yanlışlıkla
// birden fazla kez eklenip derleme hatası vermesini engeller.
#ifndef TOP_H
#define TOP_H

// Gerekli Kütüphaneler:
#include <QLabel>  // Topumuz aslında bir resim olduğu için QLabel kütüphanesini çağırıyoruz.
#include <QWidget> // Bu bir görsel bileşen olduğu için QWidget kütüphanesini çağırıyoruz.

// Sınıf Tanımı:
// "class Top : public QLabel" -> Top sınıfını oluşturuyoruz ve QLabel'den MİRAS alıyoruz.
// Yani: "Top, aslında özelleştirilmiş bir Etikettir (QLabel)" diyoruz[cite: 2].
    class Top : public QLabel
{
    Q_OBJECT // Qt'nin meta-nesne sistemini (Sinyal-Slot yapısı vb.) etkinleştiren makro.

public:
    // Yapıcı Fonksiyon (Constructor): Top nesnesi oluşturulduğunda çalışacak fonksiyon.
    // explicit: Derleyicinin kafasına göre otomatik tür dönüşümü yapmasını engeller (Kod güvenliği için).
    // QWidget *parent = nullptr: Bu topun sahibi kim? (Genelde MainWindow olur).
    // "nullptr" varsayılan değerdir, yani sahipsiz de oluşturulabilir[cite: 2].
        explicit Top(QWidget *parent = nullptr);
};

#endif // TOP_H bitişi
