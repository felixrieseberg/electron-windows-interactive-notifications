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
									"../dll/x64"
								],
							}
						}
					}],
					['target_arch=="ia32"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../dll/ia32"
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
									"../dll/x64"
								],
							}
						}
					}],
					['target_arch=="ia32"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../dll/ia32"
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