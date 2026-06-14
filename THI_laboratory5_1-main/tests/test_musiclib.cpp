#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "C:/THI/music_lib3/music_lib3.h"
#include "C:/THI/laboratory4/programm_lab4/trackfactorymethod.h"

TEST(MusicTrackTest, BasicTrackCreation) {
    PopsongFactory factory(std::string("Russian"), std::string("Soprano"));

    MUSIC_COMPOSITION* track = factory.CreateTrack("Miserere", 240);

    ASSERT_NE(track, nullptr);

    EXPECT_EQ(track->getDuration(), 240);

    delete track;
}

TEST(MusicTrackTest, ElectronicTrackPolymorphism) {
    ElectronicTrackFactory electFactory(std::string("Synthesizer"), 320);

    MUSIC_COMPOSITION* track = electFactory.CreateTrack("Techno Breeze", 300);

    ASSERT_NE(track, nullptr);

    std::string techIntro = track->technical_intro();

    EXPECT_NE(techIntro.find("Synthesizer"), std::string::npos);
    EXPECT_NE(techIntro.find("320"), std::string::npos);

    delete track;
}


TEST(MusicTrackTest, PlaylistTotalDurationCalculation) {
    std::vector<MUSIC_COMPOSITION*> testPlaylist;

    ElectronicTrackFactory f1(std::string("Synth"), 192);
    PopsongFactory f2(std::string("English"), std::string("Pop"));

    testPlaylist.push_back(f1.CreateTrack("Track One", 120));
    testPlaylist.push_back(f2.CreateTrack("Track Two", 180));

    int totalDuration = 0;
    for (auto track : testPlaylist) {
        if (track) {
            totalDuration += track->getDuration();
        }
    }

    EXPECT_EQ(totalDuration, 300);

    for (auto track : testPlaylist) {
        delete track;
    }
}

