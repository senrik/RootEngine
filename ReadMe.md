```mermaid
gantt
    title RootEngine Demo Timeline
    dateFormat DD-MM-YYYY
    section Console
        AddFunction: done, a1, 05-02-2025, 1d
        CallFunction: done, a2, 05-02-2025, 1d
        Test AddFunction: active, after a2, 1d
        Test CallFunction: active, after a2, 1d
        Input Complete: 1d
        Test Console input : 4d
    section GameWorld
        RegionGeneration Complete: active, b1, 05-02-2025, 3d
        Test RegionGeneration: after b1, 2d 
        RegionLink Complete: 2d
        Add GameWorld Commands: 5d
        Test GameWorld Commands: 2d
        

```

# RenderPipeline: C

# Roots Engine: C/C++