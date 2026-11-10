function doPost(e) {
  const sheet = SpreadsheetApp.getActiveSpreadsheet()
    .getSheetByName("Sheet1");
  const data = JSON.parse(e.postData.contents);
  sheet.appendRow([
    new Date(),
    data.location,
    data.node_id,
    data.air_temp,
    data.humidity,
    data.lux,
    data.peperomia_sm,
    data.peperomia_v_sm,
    data.batt_volt
  ]);

  return ContentService
    .createTextOutput("OK");
}
