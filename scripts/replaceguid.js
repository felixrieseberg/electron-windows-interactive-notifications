/*
  Some methods taken from https://github.com/kelektiv/node-uuid/blob/master/uuid.js
*/

const path = require('path')
const fs = require('fs')
const crypto = require('crypto')
const {replaceSync, getAppPackage} = require('./utils')

const DEFINED_CLSID = /A23D2B18-8DD7-403A-B9B7-152B40A1478C/gi

/**
 * Attempts to fetch the CLSID from the environment
 *
 * @returns {string|null} CLSID
 */
function getClsidFromEnvironment () {
  return process.env.TOAST_ACTIVATOR_CLSID || null
}

/**
 * Attempts to fetch the CLSID using a package.json present
 * in the current working directory (usually the application
 * for which `npm install` was run)
 *
 * @returns {string|null} CLSID
 */
function getClsidFromPackage () {
  let appPackage = getAppPackage() || {}
  let interativeNotifications = appPackage['interactive-notifications'] || {}

  return interativeNotifications['toast-activator-clsid'] || null
}

/**
 * Randomly generates a CLSID
 *
 * @returns {string} CLSID
 */
function generateClsid () {
  let rnds = crypto.randomBytes(16)
  let bth = []
  let i = 0

  // Set bits for version and `clock_seq_hi_and_reserved`
  rnds[6] = (rnds[6] & 0x0f) | 0x40
  rnds[8] = (rnds[8] & 0x3f) | 0x80

  for (let i = 0; i < 256; ++i) {
    bth[i] = (i + 0x100).toString(16).substr(1);
  }

  return  bth[rnds[i++]] + bth[rnds[i++]] +
          bth[rnds[i++]] + bth[rnds[i++]] + '-' +
          bth[rnds[i++]] + bth[rnds[i++]] + '-' +
          bth[rnds[i++]] + bth[rnds[i++]] + '-' +
          bth[rnds[i++]] + bth[rnds[i++]] + '-' +
          bth[rnds[i++]] + bth[rnds[i++]] +
          bth[rnds[i++]] + bth[rnds[i++]] +
          bth[rnds[i++]] + bth[rnds[i++]]
}

/**
 * Returns a CLSID, using the following methods:
 *
 *  (1) Using an environment variable
 *  (2) Using a package.json present in the current working directory
 *  (3) Using a random CLSID generator
 *
 * @returns {string} CLSID
 */
function getClsid () {
  return getClsidFromEnvironment() || getClsidFromPackage() || generateClsid()
}

/**
 * Replaces the CLSID in the C++ source files
 */
function replaceCLSID () {
  const newClsid = getClsid()
  const cppFile = path.join(__dirname, '..', 'InteractiveNotifications', 'InteractiveNotifications.cpp')

  console.log(`\n##### ToastActivitorCLSID #################################`)
  console.log(`DLLs will be compiled with the following ToastActivitorCLSID:`)
  console.log(newClsid)
  console.log(`###########################################################\n`)

  replaceSync(cppFile, DEFINED_CLSID, newClsid)
}

console.log(getClsid())

module.exports = replaceCLSID
