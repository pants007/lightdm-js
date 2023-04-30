var ldm_js = require('bindings')('lightdmjs');
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}
async function doSomething() {
  let callback_types = ldm_js.callbackTypes()
  ldm_js.setCallback(callback_types.showPromptSignal, (text, type) => {
    console.log(text)
    if (text === "login:") {
      ldm_js.authenticationRespond('pants007')
    } else {
      ldm_js.authenticationRespond('niekka007')
    }
  });
  ldm_js.setCallback(callback_types.authenticationCompleteSignal, () => {
    if (ldm_js.isAuthenticated()) {
      console.log('authentication succesful!')
    } else {
      console.log('authentication failed!')
    }
  })
  ldm_js.connectToDaemonSync()
  ldm_js.authenticationBegin();
  await sleep(500);
  ldm_js.releaseCallbacks()
}
doSomething()