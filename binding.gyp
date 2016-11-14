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
				"./InteractiveNotifications"
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
					"conditions": [
						['target_arch=="x64"', {
							"AdditionalLibraryDirectories": [
								"../x64/Debug"
							],
						}],
						['target_arch=="ia32"', {
							"AdditionalLibraryDirectories": [
								"../ia32/Debug"
							],
						}]
					]
				}
			}
		},
		"Release": {
			"msvs_settings": {
				"VCLinkerTool": {
					"conditions": [
						['target_arch=="x64"', {
							"AdditionalLibraryDirectories": [
								"../x64/Release"
							],
						}],
						['target_arch=="ia32"', {
							"AdditionalLibraryDirectories": [
								"../ia32/Debug"
							],
						}]
					]
				}
			}
		}
	  }
	}
  ]
}