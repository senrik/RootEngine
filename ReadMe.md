```mermaid
gantt
    title RootEngine Demo Timeline
    dateFormat DD-MM-YYYY
    section Console
        AddFunction: done, a1, 05-02-2025, 1d
        CallFunction: done, a2, 05-02-2025, 1d
        Test AddFunction: done, after a2, 1d
        Test CallFunction: done, after a2, 1d
        Input Complete: done, 1d
        Test Console input : done, 4d
    section GameWorld
        RegionGeneration Complete: done, b1, 05-02-2025, 3d
        Test RegionGeneration: done, after b1, 2d 
        RegionLink Complete: 2d
        Add GameWorld Commands: done, 5d
        Test GameWorld Commands: active, 2d
    section Player
        PlayerStats: active, 2d
        PlayerInventory: active, 3d
        PlayerCommands: active, 2d

```

# RenderPipeline: C

# Roots Engine: C/C++