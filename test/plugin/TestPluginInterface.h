#pragma once

class TestPluginInterface {
public:
    virtual ~TestPluginInterface() {}
    virtual void executePlugin() = 0;
};
