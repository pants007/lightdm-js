const ldm_js = require('bindings')('lightdmjs');

const defaultShowPromptCallback = (text, type) => {
  console.log(text, type)
}
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}
async function doSomething() {
  let callback_types = ldm_js.callbackTypes()
  ldm_js.setCallback(callback_types.showPrompt.signal, (text, type) => {
    console.log(text, type)
    if (type === callback_types.showPrompt.types.question) {
      ldm_js.authenticationRespond('pants007')
    } else {
      ldm_js.authenticationRespond('niekka007')
    }
  });
  ldm_js.setCallback(callback_types.authenticationComplete.signal, () => {
    if (ldm_js.isAuthenticated()) {
      console.log('authentication succesful!')
    } else {
      console.log('authentication failed!')
    }
  })
  ldm_js.connectToDaemonSync()
  ldm_js.authenticationBegin();
  await sleep(1000);
  ldm_js.releaseCallbacks()
}
// console.log(ldm_js.callbackTypes())
// console.log(ldm_js.getHints())
// doSomething()
module.exports = { ldm_js }