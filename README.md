# Starstruck

Contains code for 9393B HA Robotics Team's robot, Glamdring. Using PROS.

### Features

- Recordable autonomous programs using JINX debugger.

### JINX integration

#### Available commands

- record: Start recording a new autonomous program. Overwrites the current program if it exists.
- stop: Stops the current recording.
- reload: Reloads the autonomous program from flash. Required after recording a new autonomous program before playback.
- fsize: Returns the file size of the autonomous program.
- reboot: Deletes the current autonomous program. A reboot is required due to PROS's file system.
