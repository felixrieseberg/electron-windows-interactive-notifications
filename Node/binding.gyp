{
  "targets": [
    {
      "target_name": "notifications_bindings",
      "sources": [ 
	    "lib/notifications_bindings.cc"
	  ],
	  "libraries": [ "-lruntimeobject.lib","-lshlwapi.lib" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
		"../InteractiveNotifications"
      ],
	  "link_settings": {
		"libraries": [
			"-lInteractiveNotifications.lib",
		]
	  },
	  "configurations": {
		"Debug": {
			"msvs_settings": {
				"VCLinkerTool": {
					"AdditionalLibraryDirectories": [
						"../../Debug"
					]
				}
			}
		},
		"Release": {
			"msvs_settings": {
				"VCLinkerTool": {
					"AdditionalLibraryDirectories": [
						"../../Release"
					]
				}
			}
		}
	  }
	}
  ]
}