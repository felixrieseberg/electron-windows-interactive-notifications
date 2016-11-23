/*
  Some methods taken from https://github.com/kelektiv/node-uuid/blob/master/uuid.js
*/

const path = require('path')
const fs = require('fs')
const crypto = require('crypto')
const {replaceSync} = require('./utils')

const DEFINED_CLSID = /A23D2B18-8DD7-403A-B9B7-152B40A1478C/gi

function getClsid () {
  if (process.env.TOAST_ACTIVATOR_CLSID) return process.env.TOAST_ACTIVATOR_CLSID

  const rnds = crypto.randomBytes(16)

  // Set bits for version and `clock_seq_hi_and_reserved`
  rnds[6] = (rnds[6] & 0x0f) | 0x40
  rnds[8] = (rnds[8] & 0x3f) | 0x80

  return buff_to_string(rnds)
}

function buff_to_string (buf) {
  const i = 0
  const _byteToHex = []
  const _hexToByte = {}

  for (let ii = 0; i < 256; ++i) {
    _byteToHex[i] = (i + 0x100).toString(16).substr(1)
    _hexToByte[_byteToHex[i]] = i
  }

  const bth = _byteToHex

  return bth[buf[i++]] + bth[buf[i++]] +
    bth[buf[i++]] + bth[buf[i++]] + '-' +
    bth[buf[i++]] + bth[buf[i++]] + '-' +
    bth[buf[i++]] + bth[buf[i++]] + '-' +
    bth[buf[i++]] + bth[buf[i++]] + '-' +
    bth[buf[i++]] + bth[buf[i++]] +
    bth[buf[i++]] + bth[buf[i++]] +
    bth[buf[i++]] + bth[buf[i++]]
}

function replaceCLSID () {
  const newClsid = getClsid()
  const cppFile = path.join(__dirname, '..', 'InteractiveNotifications', 'InteractiveNotifications.cpp')

  console.log(`\n##### ToastActivitorCLSID #################################`)
  console.log(`DLLs will be compiled with the following ToastActivitorCLSID:`)
  console.log(newClsid)
  console.log(`###########################################################\n`)

  replaceSync(cppFile, DEFINED_CLSID, newClsid)
}

module.exports = replaceCLSID
