# Philosophers 🍽️

Bu proje, ünlü "Dining Philosophers Problem" (Yemek Yiyen Filozoflar Problemi) çözümünü C programlama dili ile gerçekleştirmektedir.

## Problem Açıklaması

Filozoflar problemi, bilgisayar bilimlerinde klasik bir senkronizasyon problemidir:
- N sayıda filozof bir masa etrafında oturur
- Her filozofun arasında bir çatal bulunur (N adet çatal)
- Filozoflar sadece üç şey yapar: düşünür, yer ve uyur
- Yemek yemek için iki çatala ihtiyaç duyarlar (sol ve sağ)
- Amaç: hiçbir filozofun açlıktan ölmemesini sağlamak

## Özellikler

- ✅ Çoklu iş parçacığı (pthread) kullanımı
- ✅ Mutex ile senkronizasyon
- ✅ Deadlock önleme
- ✅ Gerçek zamanlı durum takibi
- ✅ Configurable parametreler

## Kullanım

### Adım 1: Projeyi İndirme

```bash
git clone https://github.com/ayse-nur-mert/philosophers.git
cd philosophers
```

### Adım 2: Derleme

```bash
make
```

Bu komut şunları yapar:
- Tüm `.c` dosyalarını derler
- `philo` adında çalıştırılabilir dosya oluşturur
- Derlemede hata olursa detaylı bilgi verir

### Adım 3: Çalıştırma

```bash
./philo [filozof_sayısı] [ölme_süresi] [yeme_süresi] [uyuma_süresi] [her_filozofun_yemesi_gereken_sayı]
```

#### Parametreler (Detaylı):

1. **`filozof_sayısı`** (1-200): 
   - Masa etrafındaki filozof sayısı
   - Minimum: 1, Maksimum: 200
   - Önerilen: 4-10 arası test için ideal

2. **`ölme_süresi`** (milisaniye):
   - Bir filozofun son yemek yemesinden sonra ölmeden önce geçen süre
   - Bu süre geçerse filozof ölür ve simülasyon durur
   - Çok düşük değerler: Filozoflar açlıktan ölür
   - Çok yüksek değerler: Simülasyon çok uzun sürer

3. **`yeme_süresi`** (milisaniye):
   - Bir filozofun yemek yemek için harcadığı süre
   - Bu süre boyunca filozof iki çatal tutar
   - Diğer filozoflar beklemek zorunda kalır

4. **`uyuma_süresi`** (milisaniye):
   - Bir filozofun yemek yedikten sonra uyku için harcadığı süre
   - Bu süre boyunca filozof çatalları bırakır

5. **`her_filozofun_yemesi_gereken_sayı`** [İsteğe bağlı]:
   - Her filozofun yemesi gereken minimum yemek sayısı
   - Bu sayıya ulaşıldığında program başarıyla sonlanır
   - Belirtilmezse: Sonsuz döngü (manuel durdurma gerekli)

#### Detaylı Örnek Kullanımlar:

```bash
# BAŞLANGIÇ TESTİ - Basit senaryo
./philo 5 800 200 200
# 5 filozof, kimse ölmemeli, manuel durdurma gerekli (Ctrl+C)

# BAŞARI TESTİ - Belirli yemek sayısı ile bitiş
./philo 5 800 200 200 7
# Her filozof 7 kez yediğinde program otomatik durur

# ÖLÜM TESTİ - Tek filozof (kesinlikle ölmeli)
./philo 1 800 200 200
# 1 filozof, 2 çatal gerekli ama sadece 1 var → ölüm

# KRİTİK SINIR TESTİ
./philo 4 410 200 200
# Çok kritik zaman aralığı, iyi optimizasyon gerekli

# HIZLI SİMÜLASYON
./philo 4 2000 500 500
# Uzun süreler, rahat takip edilebilir

# STRES TESTİ
./philo 10 400 100 100
# Çok filozof, kısa süreler, yoğun rekabet
```

#### Program Çıktısı Nasıl Okunur:

```
0 1 has taken a fork      # 0ms'de 1 numaralı filozof çatal aldı
0 1 has taken a fork      # 0ms'de 1 numaralı filozof ikinci çatalı aldı  
0 1 is eating             # 0ms'de 1 numaralı filozof yemeye başladı
200 1 is sleeping         # 200ms'de 1 numaralı filozof uymaya başladı
400 1 is thinking         # 400ms'de 1 numaralı filozof düşünmeye başladı
```

#### Program Nasıl Durur:

1. **Başarılı Bitiş**: Tüm filozoflar yeterli sayıda yemek yerse
2. **Ölüm**: Herhangi bir filozof açlıktan ölürse
3. **Manuel Durdurma**: `Ctrl+C` ile zorunlu durdurma

#### Hata Mesajları:

```bash
# Yanlış parametre sayısı
./philo 5
# Çıktı: Usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_must_eat]

# Geçersiz değerler
./philo 0 800 200 200
# Çıktı: Hata mesajı (filozof sayısı 1'den küçük olamaz)
```

## Çıktı Formatı

Program şu formatta çıktı verir:
```
[timestamp] [philosopher_id] [action]
```

Mümkün aksiyonlar:
- `has taken a fork` - Çatal aldı
- `is eating` - Yemek yiyor
- `is sleeping` - Uyuyor
- `is thinking` - Düşünüyor
- `died` - Öldü

## Dosya Yapısı

```
├── main.c          # Ana program ve cleanup fonksiyonları
├── philo.c         # Filozof thread fonksiyonları
├── philo_init.c    # Başlatma ve mutex init fonksiyonları
├── utils1.c        # Yardımcı fonksiyonlar (time, parsing)
├── utils2.c        # Ek yardımcı fonksiyonlar
├── philo.h         # Header dosyası (struct'lar ve fonksiyon tanımları)
├── Makefile        # Derleme kuralları
└── README.md       # Bu dosya
```

## Temizlik

```bash
# Object dosyalarını temizle
make clean

# Tüm dosyaları temizle (executable dahil)
make fclean

# Yeniden derle
make re
```

## Teknik Detaylar

### Kullanılan Teknolojiler:
- **pthread**: POSIX thread kütüphanesi
- **mutex**: Paylaşılan kaynakları koruma
- **gettimeofday**: Zaman ölçümü

### Çözüm Yaklaşımı:
- Her çatal için ayrı mutex
- Ölüm kontrolü için ayrı thread
- Circular deadlock önleme stratejisi

## Test Senaryoları ve Beklenen Sonuçlar

### 🔴 Ölüm Testleri:

#### Test 1: Tek Filozof (Kesin Ölüm)
```bash
./philo 1 800 200 200
```
**Beklenen:** Filozof 800ms içinde ölmeli çünkü yemek için 2 çatal gerekli ama sadece 1 tane var.

#### Test 2: İmkansız Zaman Aralığı
```bash
./philo 4 400 200 200
```
**Beklenen:** Filozoflardan en az biri 400ms içinde ölmeli çünkü süre çok kısa.

#### Test 3: Çok Kısa Ölüm Süresi
```bash
./philo 5 200 100 100
```
**Beklenen:** Hızlı ölümler, çok zor senkronizasyon.

### 🟢 Başarılı Testler:

#### Test 4: Normal Koşullar
```bash
./philo 5 800 200 200
```
**Beklenen:** Hiç kimse ölmemeli, sonsuz döngü (Ctrl+C ile durdurun).

#### Test 5: Uzun Süreler
```bash
./philo 4 2000 500 500
```
**Beklenen:** Rahat takip edilebilir, kimse ölmemeli.

#### Test 6: Çok Filozof
```bash
./philo 10 1000 100 100
```
**Beklenen:** Yoğun rekabet ama kimse ölmemeli.

### 🎯 Yemek Sayısı Testleri:

#### Test 7: Belirli Yemek Sayısı
```bash
./philo 5 800 200 200 7
```
**Beklenen:** Her filozof 7 kez yedikten sonra program başarıyla sonlanmalı.

#### Test 8: Az Yemek Sayısı
```bash
./philo 4 1000 200 200 3
```
**Beklenen:** Hızlı bitiş, her filozof 3 kez yemeli.

### ⚡ Kritik Sınır Testleri:

#### Test 9: 410ms Sınırı
```bash
./philo 4 410 200 200
```
**Beklenen:** En kritik test, çok iyi optimizasyon gerekli.

#### Test 10: Çok Filozof + Kısa Süre
```bash
./philo 8 500 150 150
```
**Beklenen:** Zor ama başarılabilir.

### 🧪 Stres Testleri:

#### Test 11: Maksimum Filozof
```bash
./philo 200 1000 100 100
```
**Beklenen:** Sistem limitlerini test eder.

#### Test 12: Minimum Süreler
```bash
./philo 5 600 100 50
```
**Beklenen:** Çok hızlı döngü, yoğun CPU kullanımı.

### ❌ Hata Testleri:

#### Test 13: Yanlış Parametre
```bash
./philo 5
./philo 5 800
./philo 5 800 200
```
**Beklenen:** Usage mesajı göstermeli.

#### Test 14: Geçersiz Değerler
```bash
./philo 0 800 200 200
./philo -5 800 200 200
./philo 5 -800 200 200
```
**Beklenen:** Hata mesajı vermeli.

### 📊 Sonuç Değerlendirmesi:

- ✅ **Başarılı**: Program belirlenen sürede bitiyor, kimse ölmüyor
- ❌ **Başarısız**: Filozof ölüyor veya program çakışıyor
- ⏱️ **Zaman Aşımı**: Program çok uzun sürüyor (manuel durdurma gerekli)

### 🔍 Çıktı Örnekleri:

#### Başarılı Çalışma:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
2 3 has taken a fork
2 3 is eating
200 1 is sleeping
202 3 is sleeping
400 1 is thinking
402 3 is thinking
```

#### Ölüm Durumu:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
200 1 is sleeping
400 1 is thinking
410 3 died
```