# Cub3D Parser Özeti

Bu belge, Cub3D projesindeki parser mekanizmasını ve çalışma mantığını teknik ve yapısal olarak özetler.

## 1. Genel Akış
Parser, `.cub` uzantılı dosyayı okuyup doğrular ve `t_game` yapısına aktarır. İşlem sırası şöyledir:
1.  **Read File:** Tüm dosya satır satır okunur.
2.  **Texture Parsing:** Duvar dokuları (NO, SO, WE, EA) ayıklanır.
3.  **Color Parsing:** Zemin (F) ve Tavan (C) renkleri ayıklanır.
4.  **Map Parsing:** Harita verisi matrise aktarılır ve oyuncu konumu bulunur.
5.  **Validation:** Flood Fill algoritması ile haritanın etrafının kapalı olduğu doğrulanır.

## 2. Temel Fonksiyonlar

### `parsing.c`
- `read_file`: Dosyayı açar ve satırları Garbage Collector (GC) ile izleyerek bir diziye aktarır.
- `parse_file`: Parser'ın ana giriş noktasıdır; alt parser fonksiyonlarını sırayla çağırır.

### `parse_textures.c`
- `parse_textures`: "NO ", "SO " gibi ön ekleri arar ve yanındaki dosya yollarını kaydeder.
- `parse_colors`: "F " ve "C " satırlarını bulur, RGB değerlerini (`0-255`) doğrular ve tek bir integer'a çevirir.

### `parse_map.c`
- `parse_map`: Harita satırlarını bulur, matrise (`grid`) dönüştürür, yüksekliği ve genişliği hesaplar.
- `find_player_position`: `N, S, E, W` karakterlerini arayarak oyuncu koordinatlarını ve yönünü belirler.
- `flood_fill_check`: Rekürsif bir su baskını algoritması kullanarak oyuncunun ulaştığı her yerin duvarlarla çevrili olduğunu denetler.

## 3. Bellek Yönetimi (Garbage Collector)
Projede özel bir `t_gc` (Garbage Collector) yapısı kullanılır.
- **`gc_track`**: Tahsis edilen her pointer'ı bir bağlı listeye ekler.
- **`gc_malloc`**: `malloc` işlemini yapıp sonucu otomatik olarak listeye kaydeder.
- **Avantajı**: Hata anında veya program sonunda `gc_free_all` çağrılarak tüm bellek tek seferde temizlenir, böylece bellek sızıntısı (leak) oluşmaz.

---
*Not: Bu sistem Norminette kurallarına uygun olarak yapılandırılmıştır.*
