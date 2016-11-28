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
				"conditions": [
					['target_arch=="x64"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../x64/Release"
								],
							}
						}
					}],
					['target_arch=="ia32"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../Release"
								],
							}
						}
					}]
				]
			},
			"Release": {
				"conditions": [
					['target_arch=="x64"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../x64/Release"
								],
							}
						}
					}],
					['target_arch=="ia32"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../Release"
								],
							}
						}
					}]
				]
			},
	  }
	}
  ]
}