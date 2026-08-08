#pragma once

#include "mod/label/Label.h"
#include <memory>
#include <unordered_map>

namespace bps::label {

class LabelRegistry {

public:
    static void put(const std::string& id, std::shared_ptr<Label> label);
    static std::shared_ptr<Label> get(const std::string& id);
    static bool exists(const std::string& id);

private:
    static std::unordered_map<std::string, std::shared_ptr<Label>> mRegistry;

};

}