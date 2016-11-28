/*
  Some methods taken from https://github.com/kelektiv/node-uuid/blob/master/uuid.js
*/

const path = require('path')
const fs = require('fs')
const {replaceSync} = require('./utils')

const DEFINED_PROTOCOL = /slack:\/\//gi

/**
 * Attempts to get the protocol from the environment
 *
 * @returns {string|null} protocol
 */
function getProtocolFromEnvironment () {
  return process.env.TOAST_ACTIVATOR_PROTOCOL || null
}

/**
 * Attempts to get the protocol from the package.json
 * in the current working directory (usually the app for
 * which `npm intall` was run)
 *
 * @returns {string|null} protocol
 */
function getProtocolFromPackage () {
  let appPackage = getAppPackage() || {}
  let interativeNotifications = appPackage['interactive-notifications'] || {}

  return interativeNotifications.protocol || null
}

/**
 * Attempts to get the protocol to use, using the following
 * methods:
 *  (1) From the environment
 *  (2) From the package.json in the current working directory
 *
 * @returns {string}
 */
function getProtocol () {
  return getProtocolFromEnvironment() || getProtocolFromPackage()
}

/**
 * Replaces the protocol in the C++ source files
 */
function replaceProtocol () {
  const newProtocol = getProtocol()
  const cppFile = path.join(__dirname, '..', 'InteractiveNotifications', 'InteractiveNotifications.cpp')

  console.log(`\n##### ToastActivator Protocol #############################`)
  console.log(`DLLs will be compiled with the following launch protocol:`)
  console.log(newProtocol)
  console.log(`###########################################################\n`)

  replaceSync(cppFile, DEFINED_PROTOCOL, newProtocol)
}

module.exports = replaceProtocol
