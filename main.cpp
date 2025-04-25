#include <iostream>
#include <rfl/json.hpp>
#include <rfl.hpp>
#include <glaze/json.hpp>


struct HitData {
    uint16_t x{};
    uint16_t y{};
    uint16_t tot{};
};

struct EventData {
    uint16_t tag{};
    uint16_t l1id{};
    uint16_t bcid{};
    std::vector<HitData> hits;
};

template <>
struct glz::meta<HitData> {
    using T = HitData;
    static constexpr auto value = array(
            &T::x,
            &T::y,
            &T::tot
    );
};

class Event {
public:
    EventData &data() {
        return data_;
    }
    const EventData &data() const {
        return data_;
    }
        Event() = default;
        Event(const EventData &data) : data_(data) {}
        Event(EventData &&data) : data_(data) {}
    private:
        EventData data_;

};

int main() {
    const auto event =
            EventData{.l1id = 3, .bcid = 4, .hits = {{1, 2, 3}, {4, 5, 6}}};
    const std::string json_string1 = rfl::json::write<rfl::NoFieldNames>(event);
    std::cout << json_string1 <<  "\n";
    const std::string json_string2 = rfl::json::write(event);
    std::cout << json_string2 <<  "\n";
    auto event2 = rfl::json::read<EventData, rfl::NoFieldNames>(json_string1).value();

    std::cout << glz::write_json(event).value_or("error") << "\n";

    return 0;
}
