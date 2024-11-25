#include "comm/publishers.hpp"
#include "comm/subscribers.hpp"
#include <iostream>

int main()
{
    boost::asio::io_context ioContext;
    RadarRawPublisher radarRawPublisher(ioContext);
    FlyingObjectPublisher flyingObjectPublisher(ioContext);

    RadarRawSubscriber radarRawSubscriber(ioContext);
    FlyingObjectSubscriber flyingObjectSubscriber(ioContext);

    radarRawSubscriber.set_on_receive([](const std::vector<RadarRaw>& data) {
        for (const auto& radarRaw : data)
        {
            std::cout << "RadarRaw: " << radarRaw.id << ", " 
                << radarRaw.timestamp.get_seconds() << ", " 
                << radarRaw.range.get_meters() << ", " 
                << radarRaw.azimuth.get_degrees() << ", " 
                << radarRaw.radial_velocity.get_meters_per_second() << std::endl;
        }
    });

    flyingObjectSubscriber.set_on_receive([](const std::vector<FlyingObject>& data) {
        for (const auto& flyingObject : data)
        {
            std::cout << "FlyingObject: " << flyingObject.id << ", " 
                << flyingObject.timestamp.get_seconds() << ", " 
                << flyingObject.position.x.get_meters() << ", " 
                << flyingObject.position.y.get_meters() << ", " 
                << flyingObject.velocity.x.get_meters_per_second() << ", " 
                << flyingObject.velocity.y.get_meters_per_second() << std::endl;
        }
    });

    
    ioContext.run();
    radarRawSubscriber.start();
    flyingObjectSubscriber.start();

    std::vector<RadarRaw> radarRawData = {
        {1, 1000, 10.0f, 0.0f, 0.0f},
        {2, 1000, 20.0f, 0.0f, 0.0f},
        {3, 1000, 30.0f, 0.0f, 0.0f},
    };

    std::vector<FlyingObject> flyingObjectData = {
        {1, 1000, {10.0f, 10.0f}, {0.0f, 0.0f}},
        {2, 1000, {20.0f, 20.0f}, {0.0f, 0.0f}},
        {3, 1000, {30.0f, 30.0f}, {0.0f, 0.0f}},
    };

    radarRawPublisher.publish(radarRawData);
    flyingObjectPublisher.publish(flyingObjectData);

    
    return 0;
}