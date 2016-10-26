{
  "targets": [
    {
      "target_name": "notifications",
      "sources": [ "lib/notifications.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
