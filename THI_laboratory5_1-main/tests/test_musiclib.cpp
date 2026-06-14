#include <gtest/gtest.h>
#include <vector>
#include <string>

// Подключаем твои заголовочные файлы
#include "C:/THI/music_lib3/music_lib3.h"
#include "C:/THI/laboratory4/programm_lab4/trackfactorymethod.h"

// =====================================================================
// ТЕСТ 1: Проверка создания трека и работы базовых геттеров
// =====================================================================
TEST(MusicTrackTest, BasicTrackCreation) {
    // Создаем фабрику поп-музыки (передаем параметры конструктора)
    PopsongFactory factory(std::string("Russian"), std::string("Soprano"));

    // Создаем трек: Название = "Miserere", Длительность = 240 секунд
    MUSIC_COMPOSITION* track = factory.CreateTrack("Miserere", 240);

    // Проверяем, что объект успешно создался в памяти
    ASSERT_NE(track, nullptr);

    // Проверяем, что длительность записалась корректно
    EXPECT_EQ(track->getDuration(), 240);

    // Обязательно чистим память
    delete track;
}

// =====================================================================
// ТЕСТ 2: Проверка полиморфизма (что электронный трек выводит свои данные)
// =====================================================================
TEST(MusicTrackTest, ElectronicTrackPolymorphism) {
    // Создаем фабрику электронной музыки с параметрами (тип синтезатора, битрейт)
    ElectronicTrackFactory electFactory(std::string("Synthesizer"), 320);

    MUSIC_COMPOSITION* track = electFactory.CreateTrack("Techno Breeze", 300);

    ASSERT_NE(track, nullptr);

    // Получаем техническую строку, которую выводит твой класс
    std::string techIntro = track->technical_intro();

    // Проверяем, что внутри этой строки есть упоминание переданных параметров
    // (Используем std::string::npos, чтобы проверить, что подстрока НАЙДЕНА)
    EXPECT_NE(techIntro.find("Synthesizer"), std::string::npos);
    EXPECT_NE(techIntro.find("320"), std::string::npos);

    delete track;
}

// =====================================================================
// ТЕСТ 3: Проверка математики подсчета общей длительности плейлиста
// =====================================================================
TEST(MusicTrackTest, PlaylistTotalDurationCalculation) {
    std::vector<MUSIC_COMPOSITION*> testPlaylist;

    ElectronicTrackFactory f1(std::string("Synth"), 192);
    PopsongFactory f2(std::string("English"), std::string("Pop"));

    // Создаем два трека: 120 секунд и 180 секунд
    testPlaylist.push_back(f1.CreateTrack("Track One", 120));
    testPlaylist.push_back(f2.CreateTrack("Track Two", 180));

    // Имитируем цикл подсчета, который у тебя работает в refreshInterface()
    int totalDuration = 0;
    for (auto track : testPlaylist) {
        if (track) {
            totalDuration += track->getDuration();
        }
    }

    // Проверяем: 120 + 180 должно железно равняться 300
    EXPECT_EQ(totalDuration, 300);

    // Очищаем вектор
    for (auto track : testPlaylist) {
        delete track;
    }
}

// Точку входа main() писать НЕ нужно — GTest::gtest_main подключит её автоматически
