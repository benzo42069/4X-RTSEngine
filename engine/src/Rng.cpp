#include "company/engine/Rng.hpp"

namespace company::engine {

static std::uint64_t SplitMix64(std::uint64_t x) {
    x += 0x9e3779b97f4a7c15ull;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
    return x ^ (x >> 31);
}

RngStream::RngStream(std::uint64_t seed) : state_(seed ? seed : 0x123456789abcdefull) {}

std::uint32_t RngStream::NextU32() {
    std::uint64_t x = state_;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    state_ = x;
    return static_cast<std::uint32_t>((x * 0x2545F4914F6CDD1Dull) >> 32);
}

float RngStream::Next01() {
    return static_cast<float>(NextU32()) / static_cast<float>(0xFFFFFFFFu);
}

std::uint64_t RngStream::State() const { return state_; }
void RngStream::SetState(std::uint64_t s) { state_ = s; }

RngService::RngService(std::uint64_t masterSeed) : masterSeed_(masterSeed) {}

RngStream& RngService::Stream(std::uint32_t id) {
    auto it = streams_.find(id);
    if (it == streams_.end()) {
        it = streams_.emplace(id, RngStream{SplitMix64(masterSeed_ ^ id)}).first;
    }
    return it->second;
}

std::uint64_t RngService::MasterSeed() const { return masterSeed_; }

} // namespace company::engine
