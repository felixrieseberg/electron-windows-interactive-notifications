{
  'variables': {
    'WIN_VER' : 'v10',
    'USE_ADDITIONAL_WINMD' : 'false'
  },
  'includes': [ 'common.gypi' ],
  "targets": [
    {
      "target_name": "notifications",
      "sources": [ "lib/notifications.cc" ],
	  "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      'libraries': [ 'Pathcch.lib;runtimeobject.lib;shlwapi.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;-lruntimeobject.lib'],
      'conditions': [
		  ['WIN_VER=="v10"', {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalUsingDirectories' : [
                '%ProgramFiles(x86)%/Microsoft Visual Studio 14.0/VC/lib/store/references',
                '%ProgramFiles(x86)%/Windows Kits/10/UnionMetadata',
                '%ProgramFiles%/Microsoft Visual Studio 14.0/VC/lib/store/references',
                "%ProgramFiles%/Windows Kits/10/UnionMetadata",
                "%ProgramFiles%/Windows Kits/10/Include/10.0.10586.0/um"]
              }
            }
          }],
          ['USE_ADDITIONAL_WINMD=="true"', {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalUsingDirectories' : [
                '{AdditionalWinmdPath}'
                ]
               }
             }
          }]
       ],
      'msvs_settings': {
        'VCCLCompilerTool': {
            'AdditionalOptions': [ '/ZW']
        }
      }
     }
  ]
}