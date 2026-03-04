#pragma once
#include <cstdint>
#include <unordered_map>

namespace company::engine {

class RngStream {
public:
    explicit RngStream(std::uint64_t seed = 0);
    std::uint32_t NextU32();
    float Next01();
    std::uint64_t State() const;
    void SetState(std::uint64_t s);
private:
    std::uint64_t state_;
};

class RngService {
public:
    explicit RngService(std::uint64_t masterSeed = 1);
    RngStream& Stream(std::uint32_t id);
    std::uint64_t MasterSeed() const;
private:
    std::uint64_t masterSeed_;
    std::unordered_map<std::uint32_t, RngStream> streams_;
};

} // namespace company::engine
