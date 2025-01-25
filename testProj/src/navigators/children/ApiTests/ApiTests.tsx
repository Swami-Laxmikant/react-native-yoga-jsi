import {StyleSheet, Text, View} from 'react-native';
import {Button, VSpacer} from '../../../components';
import {logFomatted, runTest} from './tests';

export const ApiTests = () => {
  const runTestFn = () => {
    const testResults = runTest();
    logFomatted(testResults, true);
  };

  return (
    <View style={styles.mainContainer}>
      <VSpacer />
      <Text style={styles.text}>Check terminal to see results!</Text>
      <Button onPress={runTestFn} title={'Click to run tests'} />
    </View>
  );
};

const styles = StyleSheet.create({
  mainContainer: {
    flex: 1,
    padding: 16,
    gap: 16,
  },
  text: {
    alignSelf: 'center',
  },
});
