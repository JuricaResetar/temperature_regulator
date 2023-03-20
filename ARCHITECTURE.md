## Architecture
@startuml
object "Temperature regulator" as regulator
object "Temperature sensor" as sensor
object "Heater" as heater
object "Cooler" as cooler
object "Temperature" as temperature
note right: "Not an actual cpp object"
object "Temperature simulator" as simulator
simulator --> temperature
sensor <-- temperature
regulator <-- sensor
regulator --> cooler
regulator --> heater
heater --> temperature
cooler --> temperature

note left of simulator
Simulates external temperature
regulator for ex. sun
end note

@enduml